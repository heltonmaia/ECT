def line_slope(x, x1, y1, slope):
    return slope * (x - x1) + y1

slopes = []
h = 0.1
for _ in range(16):
    slopes.append( f_prime(1, h) )
    h /= 10


fig, axes = plt.subplots(nrows=4, ncols=4, figsize=(30, 15))
axes = axes.flatten()

x = list(range(-3, 5))
y = list(map(f, x))

x1 = 1
y1 = f(x1)
x_range = np.linspace(x1-1, x1+1, 10)

for idx, slope in enumerate(slopes): 
    
    axes[idx].plot(x, y)

    axes[idx].scatter(1, f(1), color='red', marker='o')

    axes[idx].plot( x_range, line_slope(x_range, x1, y1, slope), 'C1--', linewidth = 2)

    axes[idx].set_title(f'slope = {slope}')

plt.tight_layout()
plt.show()
