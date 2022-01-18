# specify directories
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/Stereo/KITTI04-12.yaml
# config_file=Examples/Stereo/KITTI03.yaml
seq_dir=/home/tannerliu/datasets/KITTI/dataset/sequences/

for seq in 04 05 06 07 08 09 10
do
echo "Running sequence $seq"
./Examples/Stereo/stereo_kitti $vocab_file $config_file $seq_dir$seq/ $seq.txt
echo "============================="
done
