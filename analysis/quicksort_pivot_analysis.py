import random
import time
from typing import Callable, Dict, List, Tuple


class QuickSortMetrics:
    def __init__(self):
        self.comparisons = 0
        self.swaps = 0
        self.recursive_calls = 0


def _partition(items: List[int], low: int, high: int, metrics: QuickSortMetrics, pivot_kind: str) -> int:
    if pivot_kind == "first":
        pivot_index = low
    elif pivot_kind == "last":
        pivot_index = high
    elif pivot_kind == "middle":
        pivot_index = (low + high) // 2
    else:
        raise ValueError(f"Unsupported pivot kind: {pivot_kind}")

    if pivot_index != high:
        items[pivot_index], items[high] = items[high], items[pivot_index]
        metrics.swaps += 1

    pivot_value = items[high]
    i = low

    for j in range(low, high):
        metrics.comparisons += 1
        if items[j] <= pivot_value:
            if i != j:
                items[i], items[j] = items[j], items[i]
                metrics.swaps += 1
            i += 1

    if i != high:
        items[i], items[high] = items[high], items[i]
        metrics.swaps += 1

    return i


def _quicksort(items: List[int], low: int, high: int, metrics: QuickSortMetrics, pivot_kind: str) -> None:
    metrics.recursive_calls += 1
    if low >= high:
        return

    pivot_position = _partition(items, low, high, metrics, pivot_kind)
    _quicksort(items, low, pivot_position - 1, metrics, pivot_kind)
    _quicksort(items, pivot_position + 1, high, metrics, pivot_kind)


def quicksort_with_pivot(items: List[int], pivot_kind: str) -> Tuple[List[int], Dict[str, int], float]:
    data = items[:]
    metrics = QuickSortMetrics()
    start = time.perf_counter()
    _quicksort(data, 0, len(data) - 1, metrics, pivot_kind)
    elapsed = time.perf_counter() - start
    return data, {
        "execution_time_seconds": elapsed,
        "comparisons": metrics.comparisons,
        "swaps": metrics.swaps,
        "recursive_calls": metrics.recursive_calls,
    }, elapsed


def generate_array(size: int, order: str, rng: random.Random) -> List[int]:
    if order == "random":
        return [rng.randint(0, size * 10) for _ in range(size)]
    if order == "sorted":
        return list(range(size))
    if order == "reverse_sorted":
        return list(range(size, 0, -1))
    raise ValueError(f"Unsupported order: {order}")


def benchmark() -> List[Dict[str, object]]:
    results: List[Dict[str, object]] = []
    rng = random.Random(42)
    for size in (100, 500, 1000):
        for order in ("random", "sorted", "reverse_sorted"):
            original = generate_array(size, order, rng)
            for pivot_kind in ("first", "last", "middle"):
                sorted_data, metrics, _ = quicksort_with_pivot(original, pivot_kind)
                results.append({
                    "size": size,
                    "order": order,
                    "pivot": pivot_kind,
                    "sorted": sorted_data,
                    "execution_time_seconds": metrics["execution_time_seconds"],
                    "comparisons": metrics["comparisons"],
                    "swaps": metrics["swaps"],
                    "recursive_calls": metrics["recursive_calls"],
                })
    return results


def print_results(results: List[Dict[str, object]]) -> None:
    header = (
        f"{'size':>6} {'order':>15} {'pivot':>8} {'time (s)':>12} {'comparisons':>13} {'swaps':>8} {'calls':>8}"
    )
    print(header)
    print("-" * len(header))

    for row in results:
        print(
            f"{row['size']:>6} {row['order']:>15} {row['pivot']:>8} "
            f"{row['execution_time_seconds']:>12.6f} {row['comparisons']:>13} {row['swaps']:>8} {row['recursive_calls']:>8}"
        )


if __name__ == "__main__":
    print("QuickSort Pivot Performance Analysis")
    print("-" * 80)
    results = benchmark()
    print_results(results)
