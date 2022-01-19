# specify directories
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/Tartan/Tartan.yaml
seq_dir=/home/tannerliu/datasets/Tartan/
dataPrefix=P001
# save to
save_dir=results/Tartan/
resultPrefix=test_tartan

echo "Running sequence $seq"
# gdb -ex run --args \
./Examples/Tartan/rgbd_tartan $vocab_file $config_file $seq_dir$dataPrefix$seq/ $save_dir$resultPrefix$seq.txt
echo "============================="
