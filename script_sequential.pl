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

my $sum=0;
my @timings = ();

foreach my $i (1..$N) {
  # \time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
  my $r=`\\ssh $mic "TIMEFORMAT=%R && time ./$filename $size" 2>&1`;
  $sum=$sum + $r;
  $r =~ s/^\s+|\s+$//g;
  push @timings, $r;
  print STDERR $r." ";
}

print STDERR "\n";
my @sorted = sort {$a <=> $b} @timings;
my $avg = $sum/$N;
print "[$avg, " . join(", ", @sorted) . "]";
