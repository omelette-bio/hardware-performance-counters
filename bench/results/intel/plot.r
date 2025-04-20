library(ggplot2)
library(dplyr)

# 1. Read and prepare data - ensuring consistent column names
file1_data <- read.csv("cpu_bound_intel.perf.csv") %>% 
  select(event, quantity) %>% 
  mutate(source = "perf")

file2_data <- read.csv("cpu_bound_intel.libpfm.csv") %>% 
  select(event, quantity) %>% 
  mutate(source = "libpfm")

# 2. Combine data and create positioning
combined_data <- bind_rows(file1_data, file2_data) %>% 
  # Create numeric positions for each event
  mutate(event_factor = factor(event),
         event_num = as.numeric(event_factor)) %>% 
  # Offset positions based on source
  mutate(x_pos = ifelse(source == "perf", 
                       event_num - 0.2, 
                       event_num + 0.2))

# 3. Create the plot
p <- ggplot(combined_data, aes(x = x_pos, y = quantity, fill = source)) +
  geom_col(width = 0.35) +
  # Set breaks at original event positions (not offset positions)
  scale_x_continuous(
    breaks = unique(combined_data$event_num),
    labels = levels(combined_data$event_factor)
  ) +
  scale_fill_manual(values = c("perf" = "#1f77b4", "libpfm" = "#ff7f0e")) +
  labs(title = "PMU Event Comparison : perf command vs libpfm", 
       x = "Event", 
       y = "Measurement Value",
       fill = "Data Source") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 45, hjust = 1))

print(p)