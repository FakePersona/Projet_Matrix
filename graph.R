comparaison_data <- read.table("comparaison.data",header=T)
comparaison_data

png("Comparison.png")

plot(comparaison_data, log="y")

title(main="Comparaison", col.main="red", font.main=4)

dev.off()

error_data <- read.table("error.data",header=T)
error_data

png("Error.png")

plot(error_data, log="y")

title(main="Erreurs", col.main="red", font.main=4)

dev.off()