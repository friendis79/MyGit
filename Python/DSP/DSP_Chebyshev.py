import numpy as np
import matplotlib.pyplot as plt

# Define the Chebyshev polynomial of the first kind
def chebyshev_poly_first_kind(n, x):
    if n == 0:
        return np.ones_like(x)
    elif n == 1:
        return x
    else:
        Tn_minus_one = x
        Tn_minus_two = np.ones_like(x)
        for i in range(2, n + 1):
            Tn = 2 * x * Tn_minus_one - Tn_minus_two
            Tn_minus_two = Tn_minus_one
            Tn_minus_one = Tn
        return Tn

# Define the Chebyshev filter magnitude response function
def chebyshev_magnitude_response(order, epsilon, w):
    Tn = chebyshev_poly_first_kind(order, w)
    magnitude = 1 / np.sqrt(1 + epsilon**2 * Tn**2)
    return magnitude

# Define the ripple factor delta
def ripple_factor(epsilon):
    return 1 / (1 + epsilon**2)

# Generate frequency range
w = np.linspace(-2, 2, 400)

# Define filter parameters
order = 5  # Example order
epsilon = 0.5  # Example value

# Plot the magnitude response
fig, axs = plt.subplots(2, 2, figsize=(12, 8))

# Plot magnitude response for the entire range of w
magnitude_response = chebyshev_magnitude_response(order, epsilon, w)
axs[0, 0].plot(w, magnitude_response, label=f'N={order}')
axs[0, 0].set_title('Magnitude Response (order 5)')
axs[0, 0].set_xlabel('w')
axs[0, 0].set_ylabel('|H(w)|')
axs[0, 0].legend()
axs[0, 0].grid(True)

# Plot with cos for |w| <= 1
w_cos = w[np.abs(w) <= 1]
magnitude_response_cos = chebyshev_magnitude_response(order, epsilon, w_cos)
axs[0, 1].plot(w_cos, magnitude_response_cos, 'g')
axs[0, 1].set_title('Magnitude Response with cos(|w| <= 1)')
axs[0, 1].set_xlabel('w')
axs[0, 1].set_ylabel('|H(w)|')
axs[0, 1].grid(True)

# Plot with cosh for |w| > 1
w_cosh = w[np.abs(w) > 1]
magnitude_response_cosh = 1 / np.sqrt(1 + epsilon**2 * np.cosh(np.arccosh(np.abs(w_cosh)))**2)
axs[1, 0].plot(w_cosh, magnitude_response_cosh, 'r')
axs[1, 0].set_title('Magnitude Response with cosh(|w| > 1)')
axs[1, 0].set_xlabel('w')
axs[1, 0].set_ylabel('|H(w)|')
axs[1, 0].grid(True)

# Ripple factor delta
delta = ripple_factor(epsilon)
axs[1, 1].text(0.5, 0.5, f'Ripple factor δ = {delta:.2f}', fontsize=15, ha='center')
axs[1, 1].set_axis_off()

plt.tight_layout()
plt.show()