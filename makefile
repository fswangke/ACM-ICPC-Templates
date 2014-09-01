tex:
	python convert.py
	xelatex main.tex
	xelatex main.tex

clean:
	del main.aux
	del main.log
	del main.out
	del main.pdf
	del main.toc
