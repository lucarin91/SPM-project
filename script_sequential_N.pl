#!/bin/perl
use strict;
use warnings;
use constant N => 10;
my $filename = shift or die "Usage: $0 FILENAME NUMBER\n";
my $size = shift or die "Usage: $0 FILENAME NUMBER\n";
my $N = shift || N;

my $sum = 0;
my @timings = ();
foreach my $n (1000, 4500, 10000, 45000, 100000) {
    print STDERR "\n....$n....:\n";
    foreach my $i (1 .. $N) {
        # \time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
        my $r = `\\ssh mic1 "TIMEFORMAT=%R && time ./$filename $size $n" 2>&1`;
        $sum = $sum + $r;
        $r =~ s/^\s+|\s+$//g;
        print STDERR $r." ";
    }

    print STDERR "\n";
    my $avg = $sum / $N;
    push @timings, $avg;
}
print "[".join( ", ", @timings )."]";
