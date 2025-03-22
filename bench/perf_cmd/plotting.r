library(ggplot2)

# Read CSV file
data <- read.csv("memory_bound_AMD.csv")

#print(colnames(data))

# Convert data to long format

p <- ggplot(data, aes(x = event, y = quantity, fill=event)) +
  geom_violin(trim = FALSE, scale = "width", alpha = 0.8) +
  theme_minimal() +
  scale_fill_brewer(palette = "Set3") +
  scale_y_continuous(expand = expansion(mult = c(0.05, 0.1))) +
  geom_hline(yintercept = min(mtcars$hp), linetype = "solid", color = "lightgray")

print(p)
