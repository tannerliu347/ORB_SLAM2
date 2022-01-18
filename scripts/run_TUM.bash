# specify directories
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/RGB-D/TUM1.yaml
seq_dir=/home/tannerliu/datasets/TUM/
dataPrefix=rgbd_dataset_freiburg1_
# save to
save_dir=results/TUM/
resultPrefix=fr1_

for seq in teddy floor xyz rpy plant; do
echo "Running sequence $seq"
./Examples/RGB-D/rgbd_tum $vocab_file $config_file $seq_dir$dataPrefix$seq/ $seq_dir$dataPrefix$seq/associated.txt $save_dir$resultPrefix$seq.txt
echo "============================="
done
