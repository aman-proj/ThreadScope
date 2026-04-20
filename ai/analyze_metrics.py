import json
import os
import sys

try:
    import matplotlib.pyplot as plt
except ImportError:
    print("Warning: matplotlib not installed. Try running: pip install matplotlib")
    sys.exit(1)

def analyze_and_plot():
    json_path = 'output/metrics.json'
    if not os.path.exists(json_path):
        print(f"Error: {json_path} not found. Ensure the simulator has run successfully.")
        sys.exit(1)

    with open(json_path, 'r') as f:
        metrics = json.load(f)

    # 1. Provide AI-like Textual Feedback based on heuristics reading JSON
    print("\n[AI Suggestion Engine]")
    print(f"Read metrics: {metrics}")
    score = (metrics['coalescing_efficiency'] * 40) + ((1.0 - min(1.0, metrics['divergence']/100)) * 40) + (metrics['occupancy'] * 20)
    print(f"Global Kernel Health Score: {score:.1f} / 100")

    if score < 50:
        print("Verdict: The kernel is highly unoptimized. Look at memory patterns and branch divergence.")
    elif score < 80:
        print("Verdict: The kernel is okay, but has room for optimization. Ensure no random thread accesses.")
    else:
        print("Verdict: Excellent kernel! Good coalescing and execution paths.")

    # 2. Draw matplotlib charts
    labels = ['Memory Efficiency', 'Occupancy', 'Divergence Penalty']
    # Normalize divergence penalty for plotting purpose (0 to 1, where 1 means no penalty)
    div_score = max(0, 1.0 - (metrics['divergence'] / 100))
    values = [metrics['coalescing_efficiency'], metrics['occupancy'], div_score]

    plt.figure(figsize=(8, 5))
    colors = ['blue', 'green', 'red']
    plt.bar(labels, values, color=colors)
    plt.ylim(0, 1.1)
    plt.ylabel('Normalized Score (0 to 1)')
    plt.title('GPU Kernel Performance Profile')
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    
    # Save the plot
    os.makedirs('output', exist_ok=True)
    plt.savefig('output/performance_chart.png')
    print("Saved performance profile chart to 'output/performance_chart.png'")
    # plt.show() # Uncomment to show interative plot

if __name__ == "__main__":
    analyze_and_plot()
