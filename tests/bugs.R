library(Ropj)
untar(system.file('bugs.tar.xz', package = 'Ropj'), exdir = '.')

# some files came out with column names completely wrong:
# apparently the window layer header contains a spreadsheet pointer,
# which we used to ignore until now
misordered <- read.opj('misordered.opj')[[1]]
stopifnot(
	all.equal(ncol(misordered$`Processed XYZ: IFE`), 3),
	all.equal(misordered$`Processed Data: IFE`$A, 1:46),
	all.equal(misordered$`Processed Data: IFE`$B[1], 'Processed Data: IFE')
)

# removing plots from the file above used to crash liborigin
crash <- read.opj('crash.opj')[[1]]
stopifnot(all.equal(
	misordered[!grepl('Graph|Plot|Contour', names(misordered))],
	crash[!grepl('Graph|Plot|Contour', names(crash))]
))
