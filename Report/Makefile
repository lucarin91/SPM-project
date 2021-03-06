

# Default Config Settings

SECTIONS_FILEPATH=sections.txt
BUILDNAME=example
REFS=references.bib
TEMPLATE=template.tex
# TEMPLATE=ut-thesis.tex
CSL=elsevier-with-titles


# Load in new config settings
include config.txt
cat := $(if $(filter $(OS),Windows_NT),type,cat)
SECTIONS := $(shell $(cat) $(SECTIONS_FILEPATH) )


# Perform task
.PHONY: all clean html pdf epub embed

pre:
	mkdir -p build

post:
	@echo POST

clean:
	rm -rf build

pdf: pre
	pandoc --toc -N --bibliography=$(REFS) -o ./build/$(BUILDNAME).pdf --csl=./external/csl/$(CSL).csl --template=./external/templates/$(TEMPLATE) --variable geometry:margin=1in $(SECTIONS)
	#open ./build/$(BUILDNAME).pdf

pdfsafemode: pre
	pandoc --toc -N --bibliography=$(REFS) -o ./build/$(BUILDNAME).pdf --csl=./external/csl/$(CSL).csl $(SECTIONS)
	#open ./build/$(BUILDNAME).pdf

latex: pre
	ln -s ../figures ./build/
	pandoc --toc -N --bibliography=$(REFS) -o ./build/$(BUILDNAME).tex --csl=./external/csl/$(CSL).csl --template=$(TEMPLATE) $(SECTIONS)

html: pre
	pandoc -S -5 --mathjax="http://cdn.mathjax.org/mathjax/latest/MathJax.js" --section-divs -s --biblatex --toc -N --bibliography=$(REFS) -o ./build/$(BUILDNAME).html -t html --normalize $(SECTIONS)

embed: pre
	pandoc -S --reference-links --mathjax="http://cdn.mathjax.org/mathjax/latest/MathJax.js" --section-divs -N --bibliography=$(REFS) --csl=./external/csl/$(CSL).csl -o ./build/embed.html -t html --normalize $(SECTIONS)

epub: pre
	pandoc -S -s --biblatex --toc -N --bibliography=$(REFS) -o ./build/$(BUILDNAME).epub -t epub --normalize $(SECTIONS)

default: pdf
