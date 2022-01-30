# specify directories
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/RGB-D/Tartan.yaml
seq_dir=/home/tannerliu/datasets/Tartan/
dataPrefix=carwelding/Hard/P001
# save to
save_dir=results/Tartan/
resultPrefix=Car_Hard_P001

echo "Running sequence $seq"
# gdb -ex run --args \
./Examples/RGB-D/rgbd_tartan $vocab_file $config_file $seq_dir$dataPrefix$seq/ $save_dir$resultPrefix$seq.txt
echo "============================="
