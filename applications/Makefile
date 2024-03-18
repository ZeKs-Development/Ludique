CC=em++
CFLAGS=--no-entry --pre-js ./locateFile.js  \
	-s ENVIRONMENT='web'  					\
	-s EXPORT_NAME='createModule'  			\
	-s USE_ES6_IMPORT_META=0  				\
	-s EXPORTED_FUNCTIONS='["_malloc", "_free"]'  \
	-s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "setValue"]'  \
	-s USE_SDL=2 

all: application.wasm

%.wasm: %.mjs
	
%.mjs: %.cpp
	$(CC) $< -o $@ $(CFLAGS)
	mv $*.wasm ../website/public/$*.wasm
	mv $*.mjs ../website/src/app/$*.mjs


.PHONY: clean
clean:
	rm ../website/public/*.wasm ../website/src/app/*.mjs