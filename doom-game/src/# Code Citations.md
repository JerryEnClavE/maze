# Code Citations

## License: unknown
https://github.com/drcarlo/IntoGamesDayOne/tree/50027f8b1d727db7f0d558df14b288e069deeea6/main.cpp

```
;
       if (window == NULL)
       {
           printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
           return;
       }

       renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
       if (renderer == NULL)
       {
           printf
```


## License: unknown
https://github.com/Vynnsounet/OCR/tree/bddd4ae5d8ad2a375daaf7367d1b4f2fb655be6d/src/image/Makefile

```
): $(OBJ)
       $(CC) $(OBJ) -o $@ $(LDFLAGS)

   %.o: %.c
       $(CC) $(CFLAGS) -c $< -o $@

   clean:
       rm -f $(OBJ) $
```

