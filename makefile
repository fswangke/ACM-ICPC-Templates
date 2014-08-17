
convert:
	python convert.py

tex:
	xelatex main.tex
	xelatex main.tex
#	main.pdf

clean:
	del main.aux
	del main.log
	del main.out
	del main.pdf
	del main.toc
	