CC = gcc-12
CFLAGS = -Wall -I./src -I.
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = ophiuchus
DIST_DIR = dist
BACKUP_DIR = backups

VERSION := $(shell cat VERSION.txt)
TIMESTAMP := $(shell date +%Y%m%d_%H%M%S)
ZIP_NAME = $(BACKUP_DIR)/Ophiuchus_v$(VERSION)_$(TIMESTAMP).zip
GIT_COMMIT_MSG = "Auto-update: v$(VERSION) on $(TIMESTAMP)"

.PHONY: all prepare package backup zip clean git-update auto-bump

all: auto-bump prepare $(DIST_DIR)/$(TARGET) package backup zip git-update

auto-bump:
	@echo "🔧 Auto-incrementing patch version..."
	@version=$$(cat VERSION.txt); \
	major=$$(echo $$version | cut -d. -f1); \
	minor=$$(echo $$version | cut -d. -f2); \
	build=$$(echo $$version | cut -d. -f3); \
	patch=$$(echo $$version | cut -d. -f4); \
	patch=$$((patch + 1)); \
	echo "$$major.$$minor.$$build.$$patch" > VERSION.txt; \
	echo "➡️ New Version: $$(cat VERSION.txt)"

prepare:
	mkdir -p build $(DIST_DIR)/user_glyphs $(DIST_DIR)/user_rituals $(BACKUP_DIR)

$(DIST_DIR)/$(TARGET): $(OBJ)
	$(CC) -o $(DIST_DIR)/$(TARGET) $(OBJ)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

package:
	cp -u src/config.h $(DIST_DIR)/
	cp -u assets/Ophiuchus.desktop $(DIST_DIR)/
	cp -u assets/icons/ophiuchus.png $(DIST_DIR)/
	if [ -d "data" ]; then cp -r data $(DIST_DIR)/; fi

backup:
	cp -r $(DIST_DIR) $(BACKUP_DIR)/ophiuchus_$(VERSION)_$(TIMESTAMP)

zip:
	zip -r $(ZIP_NAME) $(DIST_DIR)

git-update:
	git add .
	git commit -m $(GIT_COMMIT_MSG) || echo "No changes to commit."
	git push origin main

clean:
	rm -rf build/*
	rm -f $(DIST_DIR)/$(TARGET)
	rm -f $(BACKUP_DIR)/Ophiuchus_v*.zip
