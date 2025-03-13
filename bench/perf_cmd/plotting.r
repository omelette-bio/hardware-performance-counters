library(ggplot2)

# Read CSV file
data <- read.csv("memory_bound_INTEL.csv")

#print(colnames(data))

# Convert data to long format

p <- ggplot(data, aes(x = event, y = quantity)) +
  geom_violin(trim = FALSE, scale = "width", alpha = 0.8) +
  theme_minimal()

print(p)
