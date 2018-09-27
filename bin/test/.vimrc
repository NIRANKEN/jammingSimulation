syntax on
set number
set title
set tabstop=2
set expandtab
set shiftwidth=2
set smartindent
set showmatch
set backspace=eol
set whichwrap=b,s,h,l,<,>,[,]

augroup InsertHook
autocmd!
autocmd InsertEnter * highlight StatusLine guifg=#ccdc90 guibg=#2E4340
autocmd InsertLeave * highlight StatusLine guifg=#2E4340 guibg=#ccdc90
augroup END 

colorscheme lucius 
