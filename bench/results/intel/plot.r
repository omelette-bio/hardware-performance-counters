
data <- read.csv("all.csv", header=TRUE)
boxplot(data ~ event, data = data, col = "lightblue", outline = FALSE)


