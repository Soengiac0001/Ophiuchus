CC = gcc-12
CFLAGS = -D_DEFAULT_SOURCE -std=c11 -Wall -Wextra -Wpedantic -Wconversion -g -O2 -I./src -I.
SANITIZE = -fsanitize=undefined,address
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = ophiuchus
BACKUP_DIR = backups
DIST_DIR = dist
BUILD_DIR = build

VERSION   := $(shell cat VERSION.txt)
TIMESTAMP := $(shell date +%Y%m%d_%H%M%S)

DIST_ZIP    = $(BACKUP_DIR)/Ophiuchus_dist_v$(VERSION)_$(TIMESTAMP).zip
PROJECT_ZIP = $(BACKUP_DIR)/Ophiuchus_project_v$(VERSION)_$(TIMESTAMP).zip


VERSION := $(shell cat VERSION.txt)
TIMESTAMP := $(shell date +%Y%m%d_%H%M%S)
ZIP_NAME = $(BACKUP_DIR)/Ophiuchus_v$(VERSION)_$(TIMESTAMP).zip
GIT_COMMIT_MSG = "Auto-update: v$(VERSION) on $(TIMESTAMP)"

.PHONY: all prepare package backup zip zip-dist zip-project clean git-update auto-bump

all: auto-bump prepare $(DIST_DIR)/$(TARGET) package backup zip

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
	$(CC) $(SANITIZE) -o $(DIST_DIR)/$(TARGET) $(OBJ)

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

package:
	cp -u src/config.h $(DIST_DIR)/
	cp -u assets/Ophiuchus.desktop $(DIST_DIR)/
	cp -u assets/icons/ophiuchus.png $(DIST_DIR)/
	if [ -d "data" ]; then cp -r data $(DIST_DIR)/; fi

backup:
	cp -r $(DIST_DIR) $(BACKUP_DIR)/ophiuchus_$(VERSION)_$(TIMESTAMP)

zip: zip-dist zip-project

zip-dist:
	zip -r $(DIST_ZIP) $(DIST_DIR)

zip-project:
	zip -r $(PROJECT_ZIP) . \
	    -x "$(BACKUP_DIR)/*" \
	       "$(BUILD_DIR)/*" \
	       "*.o" \
	       "*.zip" \
	       "brain_state.dat"

git-update:
	if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then \
		echo "🔁 Running git-update (repo detected)..."; \
		git add .; \
		git commit -m $(GIT_COMMIT_MSG) || echo "No changes to commit."; \
	else \
		echo "⚠️  Skipping git-update: not a git repository."; \
	fi


clean:
	rm -rf build/*
	rm -f $(DIST_DIR)/$(TARGET)
	rm -f $(BACKUP_DIR)/Ophiuchus_v*.zip
