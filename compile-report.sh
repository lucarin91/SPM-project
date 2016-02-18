#!/bin/bash
pandoc -N --toc -s REPORT.md -o REPORT.pdf
pandoc -s README.md -o README.pdf