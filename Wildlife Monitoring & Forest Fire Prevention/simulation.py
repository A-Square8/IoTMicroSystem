import matplotlib.pyplot as plt
import time

GRID_SIZE = 10

def read_sensor_data(filename="sensor_data.txt"):
    fire_positions, animals = [], []
    try:
        with open(filename, "r") as file:
            for line in file:
                parts = line.strip().split()
                if len(parts) < 4:
                    continue  # Skip malformed lines
                
                tag = parts[0].upper()
                if tag == "FIRE":
                    x, y, temp = int(parts[1]), int(parts[2]), float(parts[3])
                    fire_positions.append((x, y, temp))
                elif tag == "ANIMAL":
                    animal_id, x, y, heat = int(parts[1]), float(parts[2]), float(parts[3]), float(parts[4])
                    if 0 <= x <= GRID_SIZE and 0 <= y <= GRID_SIZE:  # Ignore out-of-bounds animals
                        animals.append((animal_id, x, y, heat))
    except FileNotFoundError:
        print("Waiting for data...")
    return fire_positions, animals

def update_plot():
    plt.ion()
    fig, ax = plt.subplots(figsize=(8, 8))
    while True:
        ax.clear()
        ax.set_xlim(0, GRID_SIZE)
        ax.set_ylim(0, GRID_SIZE)
        ax.set_title("Wildlife & Fire Monitoring")
        ax.set_xlabel("X-Coordinate")
        ax.set_ylabel("Y-Coordinate")

        fire_positions, animals = read_sensor_data()

        for x, y, temp in fire_positions:
            ax.scatter(x, y, color="red", s=100, marker="x", label="Fire" if "Fire" not in ax.get_legend_handles_labels()[1] else "")

        for _, x, y, heat in animals:
            ax.scatter(x, y, color="blue", s=60, marker="o", label="Animal" if "Animal" not in ax.get_legend_handles_labels()[1] else "")

        handles, labels = ax.get_legend_handles_labels()
        by_label = dict(zip(labels, handles))
        ax.legend(by_label.values(), by_label.keys(), loc="upper right")

        plt.draw()
        plt.pause(1)

if __name__ == "__main__":
    update_plot()