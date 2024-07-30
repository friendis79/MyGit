import numpy as np
import matplotlib.pyplot as plt
from scipy.special import chebyt, chebyu, eval_chebyt, eval_chebyu

# Define the Chebyshev filter magnitude response function
def chebyshev_magnitude_response(order, epsilon, w):
    Tn = eval_chebyt(order, w)  # Chebyshev polynomial of the first kind
    magnitude = 1 / np.sqrt(1 + epsilon**2 * Tn**2)
    return magnitude

# Define the ripple factor delta
def ripple_factor(epsilon):
    return 1 / (1 + epsilon**2)

# Generate frequency range
w = np.linspace(-2, 2, 400)

# Define filter parameters
orders = [5]  # You can change this to generate responses for different orders
epsilon = 0.5  # Example value, you can modify this

# Plot the magnitude response
fig, axs = plt.subplots(2, 2, figsize=(12, 8))

for i, order in enumerate(orders):
    magnitude_response = chebyshev_magnitude_response(order, epsilon, w)
    
    axs[0, 0].plot(w, magnitude_response, label=f'N={order}')
    axs[0, 0].set_title('Magnitude Response (order 5)')
    axs[0, 0].set_xlabel('w')
    axs[0, 0].set_ylabel('|H(w)|')
    axs[0, 0].legend()
    axs[0, 0].grid(True)

# Example plots for different cases (w <= 1 and w > 1)
# You can add more cases or different values for w and order as needed

# Plot with cosh for |w| > 1
magnitude_response_cosh = 1 / np.sqrt(1 + epsilon**2 * np.cosh(np.arccosh(w[w > 1]))**2)
axs[0, 1].plot(w[w > 1], magnitude_response_cosh, 'g')
axs[0, 1].set_title('Magnitude Response with cosh(|w| > 1)')
axs[0, 1].set_xlabel('w')
axs[0, 1].set_ylabel('|H(w)|')
axs[0, 1].grid(True)

# Plot with cos for |w| <= 1
magnitude_response_cos = 1 / np.sqrt(1 + epsilon**2 * np.cos(np.arccos(w[w <= 1]))**2)
axs[1, 0].plot(w[w <= 1], magnitude_response_cos, 'r')
axs[1, 0].set_title('Magnitude Response with cos(|w| <= 1)')
axs[1, 0].set_xlabel('w')
axs[1, 0].set_ylabel('|H(w)|')
axs[1, 0].grid(True)

# Ripple factor delta
delta = ripple_factor(epsilon)
axs[1, 1].text(0.5, 0.5, f'Ripple factor δ = {delta:.2f}', fontsize=15, ha='center')
axs[1, 1].set_axis_off()

plt.tight_layout()
plt.show()
