" Vundle configures

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
" Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" YouCompleteMe Plugin
Plugin 'Valloric/YouCompleteMe'
let g:ycm_confirm_extra_conf = 0
let g:ycm_collect_identifiers_from_tags_files = 1

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    
"    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean   
"    - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

" gem5 code style

" Copyright (c) 2015 Advanced Micro Devices, Inc.
" All rights reserved.
"
" The license below extends only to copyright in the software and shall
" not be construed as granting a license to any other intellectual
" property including but not limited to intellectual property relating
" to a hardware implementation of the functionality of the software
" licensed hereunder.  You may use the software subject to the license
" terms below provided that you ensure that this notice is replicated
" unmodified and in its entirety in all distributions of the software,
" modified or unmodified, in source code or in binary form.
"
" Redistribution and use in source and binary forms, with or without
" modification, are permitted provided that the following conditions are
" met: redistributions of source code must retain the above copyright
" notice, this list of conditions and the following disclaimer;
" redistributions in binary form must reproduce the above copyright
" notice, this list of conditions and the following disclaimer in the
" documentation and/or other materials provided with the distribution;
" neither the name of the copyright holders nor the names of its
" contributors may be used to endorse or promote products derived from
" this software without specific prior written permission.
"
" THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
" "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
" LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
" A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
" OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
" SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
" LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
" DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
" THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
" (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
" OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"
" Authors: Anthony Gutierrez


" this vimrc file helps users follow the gem5 style guide see:
" www.gem5.org/Coding_Style
" it highlights extraneaous whitespace and tabs (so you can easily remove
" them), sets column length to a max of 78 characters, expands tabs, and sets
" a tab width of 4 spaces.

" *NOTE 1* this doesn't guarantee that your code with fit the style guidelines,
" so you should still to double check everything, but it helps with a lot of
" tedious stuff.

" *NOTE 2* if you do actually NEED to use a tab, e.g., in a Makefile, enter
" insert mode and type ctrl-v first, which will make tabs behave as expected

filetype indent on "auto indenting
set tabstop=4 "tabs = 4 spaces
set shiftwidth=4 "auto indent = 4 spaces
set expandtab "expand tabs to spaces
set tw=78 "max cols is 78

" highlight extrawhite space with light blue background
highlight ExtraWhitespace ctermbg=lightblue guibg=lightblue
match ExtraWhitespace /\s\+$\|\t/

" stuff to prevent the light blue highlighting from showing up at the end of
" lines when you're in insert mode. i.e., everytime you enter a space as you're
" entering text the highlighting will kick in, which can be annoying. this will
" make the highlighting only show up if you finish editing and leave some extra
" whitespace
autocmd BufWinEnter * match ExtraWhitespace /\s\+$\|\t/
autocmd InsertEnter * match ExtraWhitespace /\s\+\%#\@<!$\|\t\%#\@<!/
autocmd InsertLeave * match ExtraWhitespace /\s\+$\|\t/
autocmd BufWinLeave * call clearmatches()


" optionally set a vertical line on column 79. anything on, or after the line
" is over the limit. this can be useful as set tw=78 won't breakup existing
" lines that are over the limit, and the user can also do certain things to
" make lines go past the set textwidth, e.g., joining a line (shift-j or J)

if exists('+colorcolumn')
    set colorcolumn=79
endif


" optionally set spell checking
" set spell

" optionally highlight whitespace with specified characters. tab for trailing
" tabs, trail for trailing whitespace, extends for lines that extend beyond
" screen when wrap is off, and non-breakable white spaces. list must be set
" for these characters to display.
set list
set listchars=tab:›\ ,trail:•,extends:#,nbsp:.


" personal vim setup
set nu
syntax on
set showmatch
set hlsearch
set incsearch
set mouse=a
set paste
" set ctags
set tags+=tags,~/gem5/.gem5_tags
" enable RGB 256
set t_Co=256
set clipboard=unnamed
set backspace=2
set softtabstop=4
set smartindent
set ruler
