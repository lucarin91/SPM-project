#!/bin/perl -w
use warnings;
use strict;
use constant N => 10;
my $filename = shift or die "Usage: $0 FILENAME NUMBER\n";
my $size = shift or die "Usage: $0 FILENAME NUMBER\n";
my @json = ();

print "[\n";
foreach my $p (1,2,3,4,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80) {
  my $sum=0;
  my @timings = ();

  print STDERR "$p: ";
  foreach my $i (1..N) {
    #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
    my $r=`\\ssh mic1 "TIMEFORMAT=%R && time ./$filename $p $size" 2>&1`;
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
