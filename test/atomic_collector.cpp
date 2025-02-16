// <copyright file="atomic_collector.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(atomic_collector_test) {

    TEST_METHOD(single_threaded) {
        atomic_collector<int, 2> collector;
        {
            int fortytwo = 42;
            collector.push(fortytwo);
        }
        collector.emplace(17);
        collector.emplace(std::move(19));

        auto result = collector.reset();
        Assert::AreEqual(std::size_t(3), result.size(), L"# of elements collected", LINE_INFO());
        Assert::IsFalse(std::find(result.begin(), result.end(), 42) == result.end(), L"Found 42", LINE_INFO());
        Assert::IsFalse(std::find(result.begin(), result.end(), 17) == result.end(), L"Found 17", LINE_INFO());
        Assert::IsFalse(std::find(result.begin(), result.end(), 19) == result.end(), L"Found 19", LINE_INFO());
        Assert::IsTrue(std::find(result.begin(), result.end(), 21) == result.end(), L"Did not find 21", LINE_INFO());
    }

    TEST_METHOD(multi_threaded) {
        static constexpr std::size_t cnt = 16;
        atomic_collector<std::size_t> collector;
        std::atomic<std::size_t> done = 0;

        std::thread([&collector, &done]() {
            for (std::size_t i = 0; i < cnt; ++i) {
                collector.push(i);
                std::this_thread::yield();
            }
            ++done;
        }).detach();

        std::thread([&collector, &done]() {
            for (std::size_t i = 0; i < cnt; ++i) {
                collector.push(i);
                std::this_thread::yield();
            }
            ++done;
        }).detach();

        std::thread([&collector, &done]() {
            for (std::size_t i = 0; i < cnt; ++i) {
                collector.push(i);
                std::this_thread::yield();
            }
            ++done;
        }).detach();

        std::thread([&collector, &done]() {
            for (std::size_t i = 0; i < cnt; ++i) {
                collector.push(i);
                std::this_thread::yield();
            }
            ++done;
        }).detach();


        while (done < 4) {
            std::this_thread::yield();
        }

        auto result = collector.reset();
        Assert::AreEqual(std::size_t(4 * cnt), result.size(), L"# of elements collected", LINE_INFO());
        Assert::AreEqual(std::ptrdiff_t(4), std::count_if(result.begin(), result.end(), [](std::size_t i) { return i == 0; }), L"# of zeros", LINE_INFO());
        Assert::AreEqual(std::ptrdiff_t(4), std::count_if(result.begin(), result.end(), [](std::size_t i) { return i == 1; }), L"# of ones", LINE_INFO());
        Assert::AreEqual(std::ptrdiff_t(4), std::count_if(result.begin(), result.end(), [](std::size_t i) { return i == 4; }), L"# of fours", LINE_INFO());
    }

    TEST_METHOD(perf_test) {
        static std::size_t cnt_tasks = std::thread::hardware_concurrency();
        static constexpr std::size_t cnt_writes = 131072;
        static constexpr std::size_t page_size = 4096;
        std::chrono::milliseconds elapsed_collector;
        std::chrono::milliseconds elapsed_mutex;

        {
            atomic_collector<std::size_t, page_size> collector;
            std::atomic<std::size_t> cnt = 0;

            const auto begin = std::chrono::steady_clock::now();

            for (std::size_t i = 0; i < cnt_tasks; ++i) {
                std::thread([&collector, &cnt]() {
                    for (std::size_t i = 0; i < cnt_writes; ++i) {
                        collector.push(i);
                    }
                    ++cnt;
                }).detach();
            }

            while (cnt < cnt_tasks) {
                std::this_thread::yield();
            }

            const auto end = std::chrono::steady_clock::now();
            elapsed_collector = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            const auto result = collector.reset();
            Assert::AreEqual(cnt_writes * cnt_tasks, result.size(), L"All collected", LINE_INFO());
#if (defined(DEBUG) || defined(_DEBUG))
            Assert::AreEqual(cnt_writes * cnt_tasks / page_size, result.pages(), L"# of pages", LINE_INFO());
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

            {
                std::stringstream msg;
                msg << "elapsed_collector " << elapsed_collector.count() << std::endl;
                Logger::WriteMessage(msg.str().c_str());
            }
        }

        {
            std::vector<std::size_t> collection;
            std::mutex mutex;
            std::atomic<std::size_t> cnt = 0;

            const auto begin = std::chrono::steady_clock::now();

            for (std::size_t i = 0; i < cnt_tasks; ++i) {
                std::thread([&collection, &mutex, &cnt]() {
                    for (std::size_t i = 0; i < cnt_writes; ++i) {
                        std::lock_guard<std::mutex> l(mutex);
                        collection.push_back(i);
                    }
                    ++cnt;
                }).detach();
            }

            while (cnt < cnt_tasks) {
                std::this_thread::yield();
            }

            const auto end = std::chrono::steady_clock::now();
            elapsed_mutex = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

            Assert::AreEqual(cnt_writes * cnt_tasks, collection.size(), L"All collected", LINE_INFO());

            std::stringstream msg;
            msg << "elapsed_mutex " << elapsed_mutex.count() << std::endl;
            Logger::WriteMessage(msg.str().c_str());
        }

        Assert::IsTrue(elapsed_collector <= elapsed_mutex, L"Collector is not slower", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
