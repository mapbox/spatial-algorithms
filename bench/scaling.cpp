#include <benchmark/benchmark.h>
#include <cstdlib>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/scaling.hpp>

using namespace mapbox::geometry;
namespace op = algorithms;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
static void BM_scale_point(benchmark::State& state) // NOLINT google-runtime-references
{
    while (state.KeepRunning())
    {
        point<double> input{(rand() % 500) / 25.0, (rand() % 500) / 25.0};
        double scale = 2.5;
        auto output = op::scale<double, double>(input, scale);
        benchmark::DoNotOptimize(output.x);
    }
}

BENCHMARK(BM_scale_point);

#pragma GCC diagnostic pop
