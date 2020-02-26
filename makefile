.PHONY: clean

Um = um
DIR_SRC = src
DIR_OBJ = bin
DIR_OUTPUT = output
TARGET = ${DIR_OBJ}/bin

All: $(DIR_OBJ) $(TARGET)

$(DIR_OBJ):
	mkdir bin

$(TARGET): ${DIR_OBJ}/$(Um).o 
	gcc -o $@ $^
	
$(DIR_OBJ)/$(Um).o: ${DIR_SRC}/$(Um).c
	gcc -o $@ -c $^

run: $(TARGET)
	./$(TARGET) data/sandmark.umz > ./${DIR_OUTPUT}/outSandmark;
	./$(TARGET) data/codex.umz > ./${DIR_OUTPUT}/outCodex;
checkSandmark:
	more ./${DIR_OUTPUT}/outSandmark	
checkCodex:
	more ./${DIR_OUTPUT}/outCodex
clean:
	rm -rf $(DIR_OBJ)