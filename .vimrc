colorscheme elflord
set shiftwidth=4
set tabstop=4
syntax on
set cin
set ai
set smarttab
set smartindent
set expandtab
autocmd filetype cpp nnoremap<C-b> :!g++ % -std=c++11 -O2 -DONPC -o %:r && ./%:r <CR>
autocmd filetype cpp nnoremap<C-y> :!g++ % -std=c++1z -DONPC -fsanitize=address -g -Wall -Wextra -o %:r && ./%:r <CR>
au BufNewFile *.cpp 0r ~/.vim/sf/std.cpp
nmap <c-s> :w<CR>
imap <c-s> <Esc>:w<CR>a
map <C-l> :tabnext<cr>
map <C-h> :tabprev<cr>
map <C-t> :tabnew <cr>
map <C-w> :q! <cr>
set number
set backspace=indent,eol,start
color jellybeans
syntax enable
set autochdir
