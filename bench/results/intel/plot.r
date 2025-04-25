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
ggplot(combined_data, aes(x = event, y = quantity, fill = source)) +
  geom_col(position = position_dodge(width = 0.7), width = 0.6) +
  scale_fill_manual(values = c("perf" = "#1f77b4", "libpfm" = "#ff7f0e")) +
  labs(title = "PMU Event Comparison", 
       x = "Event", 
       y = "Measurement Value",
       fill = "Data Source") +
  theme_minimal() +
  theme(axis.text.x = element_text(angle = 45, hjust = 1))


ggsave("plot.pdf")