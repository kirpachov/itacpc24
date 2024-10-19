# Es i

## Run
```bash
clear; g++ main.cpp -o main && time ./main < samples-I/1.in
```

## Generate samples
```ruby
File.write("10000x10000", %(#{"." * 10000}\n) * 10000)
```