
d <- read.table("inv.data",header=T)


png("Comparaison.png")

x <- d$n
y <- d$mean
sd <- d$sd
x1 <- x[seq(2,length(x),2)]
x2 <- x[seq(1,length(x),2)]
y1 <- y[seq(2,length(y),2)]
y2 <- y[seq(1,length(y),2)]


plot (x, y, log="y",xlab="n",ylab="log(temps(sec))")
lines(x1,y1,col="blue")
lines(x2,y2,col="red")
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



error_data <- read.table("error.data")
error_data

png("Error.png")

plot(error_data, log="y", xlab="n", ylab="log(erreur)")

title(main="Erreurs", col.main="red", font.main=4)

dev.off()