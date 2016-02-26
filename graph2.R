
d <- read.table("test.data",header=T)

png("test.png")

x <- d$n
y <- d$mean
sd <- d$sd

plot (x, y, log="y")
epsilon = 0.02
for(i in 1:length(sd)) 
{
    up = y[i] + sd[i]*100
    low = y[i] - sd[i]*100
    segments(x[i],low , x[i], up)
    segments(x[i]-epsilon, up , x[i]+epsilon, up)
    segments(x[i]-epsilon, low , x[i]+epsilon, low)
}
