subrender
=======

subrender lets you generate beautiful animations of your logged dives. It is written in  
C++ and Qt in order to achieve maximum platform independence.  

Compiling subrender
------------------------------

Run

    qmake
    make

If you use Linux you can install subrender right away with `make install`

Input
-------

The input format is XML produced by subsurface [1](https://github.com/torvalds/subsurface),[2](http://subsurface.hohndel.org/).  
The syntax is pretty easy and can be edited by hand without using subsurface (e.g. if you don't have a data cable)  
See `example/dive328.xml` for an example dive.

Output
----------

The output format is currently `.png` only. Each frame will be written to a file, which can then be used together with other  
programs to create movies or animated images (like `gif`, `mng`, etc.).

Using the frames
-------------------------

If you have `ffmpeg` installed, you can generate a lossless movie by invoking  

```
ffmpeg -r 15 -sameq -i subrender-dive328-frame-%d.png -vcodec png dive328.mov
```  

You can then use `dive328.mov` in your preferred video editing software.

Example Dive
--------------------

You can watch the dive `example/dive328.xml` on [Vimeo](http://vimeo.com/46987032) or [Youtube](http://www.youtube.com/watch?v=PzeXe9Wc1fE)

License and Copyright
--------------------------------

Copyright (c) 2012 Maximilian Güntner <maximilian.guentner@gmail.com> under the GPL v3

