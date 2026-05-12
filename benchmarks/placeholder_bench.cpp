#include <benchmark/benchmark.h>

#include "core/vexdb.h"

static void BM_Placeholder(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(vexdb::version_major());
    }
}

BENCHMARK(BM_Placeholder);