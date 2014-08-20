
syntax on
syntax enable
set nocompatible
set backspace=indent,eol,start
set autoindent
set mouse=a
set tabstop=4
set shiftwidth=4
set ai
set number
set hlsearch incsearch
set guifont=Consolas:h16
set whichwrap=b,s,<,>,[,]
au GUIEnter * simalt ~x

set nu mouse=a nobk hls ai si ts=4 sts=4 sw=4 foldmethod=marker
"set nowrap, et
"set t_Co=256
set foldmethod=marker

nmap <C-A> ggVG
vmap <C-C> "+y

set fileencodings=ucs-bom,utf-8,cp936,gb18030,gb2312,gbk,big5,euc-jp,euc-kr,latin1

autocmd BufRead,BufNewFile *.cpp,*.java,*.tex,*.py,*.cc,*.h map<F4> : !gedit % <CR>
autocmd BufRead,BufNewFile *.cpp,*.java,*.py,*.cc map<F3> : vnew %<.in <CR>

autocmd BufRead,BufNewFile *.h map<F9> : !g++ -Wall -g3 test.cpp -o test <CR>
"autocmd BufNewFile make_data.cpp 0r $HOME/Template/make_data.cpp
autocmd BufNewFile *.cpp 0r $HOME/Template/cpp_template.cpp
"autocmd BufRead,BufNewFile *.cpp,*.h set foldmethod=indent foldlevel=99
autocmd BufRead,BufNewFile *.cpp,*.cc map<F12> : !g++ -Wall -g3 % -o %< -O2<CR>
autocmd BufRead,BufNewFile *.cpp,*.cc map<F9> : !g++ -Wall -g3 % -o %< <CR>
autocmd BufRead,BufNewFile *.cpp,*.cc map<F8> : !time ./%< < %<.in <CR>
autocmd BufRead,BufNewFile *.cpp,*.cc map<F5> : !time ./%< <CR>
autocmd BufRead,BufNewFile *.cpp,*.h set cindent

autocmd BufNewFile *.java 0r $HOME/Template/java_template.java
autocmd BufRead,BufNewFile *.java map<F9> : !javac % <CR>
autocmd BufRead,BufNewFile *.java map<F8> : !java %< < %<.in <CR>
autocmd BufRead,BufNewFile *.java map<F5> : !java %< <CR>

autocmd BufNewFile *.tex 0r $HOME/Template/TeXTemplate.tex
autocmd BufRead,BufNewFile *.tex map<F9>	: !pdflatex % <CR>
autocmd BufRead,BufNewFile *.tex map<F10>	: !latex % <CR>
autocmd BufRead,BufNewFile *.tex map<F11>	: !dvipdfm %<.dvi <CR>
autocmd BufRead,BufNewFile *.tex map<F12>	: !xelatex % <CR>
autocmd BufRead,BufNewFile *.tex map<F8>	: !okular %<.pdf <CR>
autocmd BufRead,BufNewFile *.tex map<F5>	: !google-chrome %<.pdf <CR>

autocmd BufRead,BufNewFile *.pas map<F9> : !fpc -g % <CR>

autocmd BufNewFile *.sh 0r $HOME/Template/shellScript.sh

autocmd BufNewFile *.py 0r $HOME/Template/pythonScript.py
autocmd BufRead,BufNewFile *.py set foldmethod=indent et sta sw=4 sts=4 foldlevel=99
autocmd BufRead,BufNewFile *.py map<F9> : !chmod +x % <CR>
autocmd BufRead,BufNewFile *.py map<F8> : !./% < %<.in <CR>
autocmd BufRead,BufNewFile *.py map<F5> : !./% <CR>

autocmd BufRead,BufNewFile *.markdown set sw=8 sts=8 ts=8 sta
autocmd BufRead,BufNewFile *.markdown map<F9> : !markdown % >%<.html <CR>
