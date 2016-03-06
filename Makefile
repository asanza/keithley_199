all: doc

doc:
	mkdocs build

clean:
	mkdocs build --clean
