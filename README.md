Intermittent fetch error in libgit2 on MacOS, probably TLS problem.

To compile this program on MacOS:

```
brew install libgit2
clang test.c -o test $(pkg-config --libs --cflags libgit2)
```

And then run it:

```
rm -Rf output
./test
```

Sometimes it works, but once in a while it will hang at the last object (and after a few minutes error):

```
Transferred 9311 of 9312 objects...
  SecureTransport error: connection closed via error
```

You can also see this problem in the github action: https://github.com/jeroen/libgit2-macos-bug/actions
