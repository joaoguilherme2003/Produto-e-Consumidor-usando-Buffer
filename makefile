bin: pro_con_buffer.c
	gcc $< -o $@ -pthread

.PHONY: run clean

run:
	./bin

clean:
	rm bin
