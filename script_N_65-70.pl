#!/bin/perl
use strict;
use warnings;
use constant N => 10;
my $filename = shift or die "Usage: $0 FILENAME NUMBER\n";
my $size = shift or die "Usage: $0 FILENAME NUMBER\n";
my $N = shift || N;
my $mic = shift || "mic1";

if ($mic ne "mic1") {
  my $r = `\\scp $filename $mic:`;
  print STDERR "upload file $r to $mic ..";
}

print "[\n";
foreach my $n (0, 1000, 4500, 10000, 45000) {
    my @json = ();
    print STDERR "\n....$n....:\n";
    foreach my $p (65, 70) {
        my $sum = 0;
        my @timings = ();

        print STDERR "$p: ";
        foreach my $i (1 .. $N) {
            # \time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
            my $r = `\\ssh $mic "TIMEFORMAT=%R && time ./$filename $p $size $n" 2>&1`;
            $sum = $sum + $r;
            $r =~ s/^\s+|\s+$//g;
            push @timings, $r;
            print STDERR "$r ";
        }
        print STDERR "\n";
        my @sorted = sort {$a <=> $b} @timings;
        my $avg = $sum / $N;
        push @json, "[$p, $avg, ".join(", ", @sorted )."]";
    }
    print "[\n".join( ",\n", @json )."\n]";
    print ",\n" if ($n!=45000);
}
print "\n]";
