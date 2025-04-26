CC = gcc-12
CFLAGS = -Wall -I./src -I.
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = ophiuchus
DIST_DIR = dist
BACKUP_DIR = backups
ZIP_NAME = Ophiuchus_$(shell date +%Y%m%d_%H%M%S).zip

all: prepare $(TARGET) package backup zip

prepare:
	mkdir -p build $(DIST_DIR)/user_glyphs $(DIST_DIR)/user_rituals $(BACKUP_DIR)

$(TARGET): $(OBJ)
	$(CC) -o $(DIST_DIR)/$(TARGET) $(OBJ)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

package:
	cp -u README.md $(DIST_DIR)/
	cp -u src/config.h $(DIST_DIR)/
	if [ -d "data" ]; then cp -r data $(DIST_DIR)/; fi

backup:
	cp -r $(DIST_DIR) $(BACKUP_DIR)/ophiuchus_0_0_8_$(shell date +%Y%m%d_%H%M%S)

VERSION = 1.0.0.7
ZIP_NAME = Ophiuchus_v$(VERSION)_$(shell date +%Y%m%d_%H%M%S).zip

zip:
	zip -r $(ZIP_NAME) $(DIST_DIR)



clean:
	rm -rf build $(DIST_DIR) *.zip
