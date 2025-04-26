CC = gcc-12
CFLAGS = -Wall -I./src -I.
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = ophiuchus
DIST_DIR = dist
BACKUP_DIR = backups
VERSION = 1.0.0.8
TIMESTAMP = $(shell date +%Y%m%d_%H%M%S)
ZIP_NAME = $(BACKUP_DIR)/Ophiuchus_v$(VERSION)_$(TIMESTAMP).zip
GIT_COMMIT_MSG = "Auto-update: v$(VERSION) on $(TIMESTAMP)"

git-update:
	git add .
	git commit -m $(GIT_COMMIT_MSG) || echo "No changes to commit."
	git push origin main

.PHONY: all prepare package backup zip clean git-update

all: prepare $(DIST_DIR)/$(TARGET) package backup zip

prepare:
	mkdir -p build $(DIST_DIR)/user_glyphs $(DIST_DIR)/user_rituals $(BACKUP_DIR)

$(DIST_DIR)/$(TARGET): $(OBJ)
	$(CC) -o $(DIST_DIR)/$(TARGET) $(OBJ)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

package:
	cp -u src/config.h $(DIST_DIR)/
	if [ -d "data" ]; then cp -r data $(DIST_DIR)/; fi

backup:
	cp -r $(DIST_DIR) $(BACKUP_DIR)/ophiuchus_$(VERSION)_$(TIMESTAMP)

zip:
	zip -r $(ZIP_NAME) $(DIST_DIR)

clean:
	rm -rf build $(DIST_DIR) $(BACKUP_DIR)/Ophiuchus_v*.zip
