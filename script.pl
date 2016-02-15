#!/bin/perl -w
use warnings;
use strict;
use constant N => 5;
my $SIZE = 2048;
my $STEP = 1000;
my @json = ();

print "[\n";
foreach my $p (10,12,14,16,18,20,25,30,35,40,50,60,80) {
  my $sum=0;
  my @timings = ();

  print STDERR "$p: ";
  foreach my $i (1..N) {
    #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
    my $r=`\\ssh mic1 "TIMEFORMAT=%R && time ./main.out $SIZE $STEP $p" 2>&1`;
    $sum=$sum + $r;
    $r =~ s/^\s+|\s+$//g;
    push @timings, $r;

    print STDERR $r." ";
  }
  print STDERR "\n";
  my @sorted = sort {$a <=> $b} @timings;
  my $avg = $sum/N;
  push @json, "[$p, $avg, " . join(", ", @sorted) . "]";
}
print join(",\n", @json) . "\n]\n";
