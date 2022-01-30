# specify directories
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/Stereo/Tartan.yaml
seq_dir=/home/tannerliu/datasets/Tartan/
dataPrefix=abandonedfactory_night/P001
# save to
save_dir=results/Tartan/
resultPrefix=AbandonNight_Easy_P001.txt

echo "Running sequence $seq"
# gdb -ex run --args \
./Examples/Stereo/stereo_tartan $vocab_file $config_file $seq_dir$dataPrefix$seq/ $save_dir$resultPrefix$seq.txt
echo "============================="
