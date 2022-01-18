# specify directories
bin_file=Examples/Stereo/stereo_euroc
vocab_file=Vocabulary/ORBvoc.txt
config_file=Examples/Stereo/EuRoC.yaml
seq_dir=EuRoc
timestamp_dir=Examples/Stereo/EuRoC_TimeStamps

for seq in MH03 V102 V202
do
echo "Running sequence $seq"
$bin_file $vocab_file $config_file $seq_dir/$seq/mav0/cam0/data $seq_dir/$seq/mav0/cam1/data $timestamp_dir/$seq.txt $seq.txt
echo "============================="
done

# ./Examples/Stereo/stereo_euroc Vocabulary/ORBvoc.txt Examples/Stereo/EuRoC.yaml EuRoc/mav0/cam0/data EuRoc/mav0/cam1/data Examples/Stereo/EuRoC_TimeStamps/MH01.txt 