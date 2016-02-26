
d <- read.table("inv.data",header=T)


png("Comparaison.png")

x <- d$n
y <- d$mean
sd <- d$sd


plot (x, y, log="y")
epsilon = 0.02
for(i in 1:length(sd)) 
{
    up = y[i] + sd[i]
    low = y[i] - sd[i]
    segments(x[i],low , x[i], up)
    segments(x[i]-epsilon, up , x[i]+epsilon, up)
    segments(x[i]-epsilon, low , x[i]+epsilon, low)
}

dev.off()



error_data <- read.table("error.data",header=T)
error_data

png("Error.png")

plot(error_data, log="y")

title(main="Erreurs", col.main="red", font.main=4)

dev.off()