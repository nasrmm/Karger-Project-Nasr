import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

# Plot 1: success probability
for graph_type in df["graph"].unique():
    data = df[df["graph"] == graph_type]

    plt.plot(
        data["n"],
        data["success_rate"],
        marker="o",
        label=graph_type
    )

bound = df[df["graph"] == "cycle"]

plt.plot(
    bound["n"],
    bound["theoretical_bound"],
    marker="o",
    linestyle="--",
    label="theoretical lower bound"
)

plt.xlabel("Number of vertices")
plt.ylabel("Success probability")
plt.title("Karger Success Probability")
plt.legend()
plt.grid(True)
plt.savefig("success_probability.png")
plt.close()


# Plot 2: runtime
for graph_type in df["graph"].unique():
    data = df[df["graph"] == graph_type]

    plt.plot(
        data["n"],
        data["karger_time_ms"],
        marker="o",
        label=f"Karger - {graph_type}"
    )

plt.xlabel("Number of vertices")
plt.ylabel("Time for 5000 trials (ms)")
plt.title("Karger Runtime by Graph Family")
plt.legend()
plt.grid(True)
plt.savefig("karger_runtime.png")
plt.close()


# Plot 3: exact baseline runtime
for graph_type in df["graph"].unique():
    data = df[df["graph"] == graph_type]

    plt.plot(
        data["n"],
        data["exact_time_ms"],
        marker="o",
        label=graph_type
    )

plt.xlabel("Number of vertices")
plt.ylabel("Exact min-cut runtime (ms)")
plt.title("Exact Brute-Force Runtime")
plt.legend()
plt.grid(True)
plt.savefig("exact_runtime.png")
plt.close()