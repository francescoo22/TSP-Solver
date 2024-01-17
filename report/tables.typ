#let cplex25 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [*Size: 25*], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [396],
  [tsp25_2.dat], [261.913], [777],
  [tsp25_3.dat], [247.435], [356],
  [tsp25_4.dat], [255.933], [486],
  [tsp25_5.dat], [59.6016], [250],
  [tsp25_6.dat], [237.891], [978],
  [tsp25_7.dat], [129.884], [541],
  [tsp25_8.dat], [172.776], [350],
  [tsp25_9.dat], [222.682], [524],
  [tsp25_10.dat], [121.672], [227]
)

#let cplex50 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [*Size: 50*], [*Solution*], [*Execution time (ms)*],
  [tsp50_1.dat], [243.28], [27612],
  [tsp50_2.dat], [307.205], [31282],
  [tsp50_3.dat], [228.997], [24399],
  [tsp50_4.dat], [272.981], [8980],
  [tsp50_5.dat], [330.537], [18037],
  [tsp50_6.dat], [199.451], [1685],
  [tsp50_7.dat], [253.743], [30895],
  [tsp50_8.dat], [298.338], [1050545],
  [tsp50_9.dat], [283.377], [23210],
  [tsp50_10.dat], [288.651], [18632]
)

#let cplex75 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [*Size: 75*], [*Solution*], [*Execution time (ms)*],
  [tsp75_1.dat], [352.863], [113697],
  [tsp75_2.dat], [366.408], [38108],
  [tsp75_3.dat], [268.928], [281109],
  [tsp75_4.dat], [327.206], [55524],
  [tsp75_5.dat], [421.207], [130561],
  [tsp75_6.dat], [375.023], [96416],
  [tsp75_7.dat], [366.794], [49496],
  [tsp75_8.dat], [406.919], [94832],
  [tsp75_9.dat], [245.736], [61522],
  [tsp75_10.dat], [382.569], [99251],
)

#let cplex100 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [*Size: 100*], [*Solution*], [*Execution time (ms)*],
  [tsp100_1.dat], [413.422], [400411],
  [tsp100_2.dat], [393.576\*], [2700384],
  [tsp100_3.dat], [410.009], [191136],
  [tsp100_4.dat], [353.605\*], [2700324],
  [tsp100_5.dat], [387.885], [1049424],
  [tsp100_6.dat], [373.489], [153525],
  [tsp100_7.dat], [384.87\*], [2700329],
  [tsp100_8.dat], [445.239], [254333],
  [tsp100_9.dat], [415.534], [1912922],
  [tsp100_10.dat], [413.223], [205023]
)

#let cplex200 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [*Size: 200*], [*Solution*], [*Execution time (ms)*],
  [tsp200_1.dat], [618.972\*], [2701295]
)

#let calibration_exact_values = (
  179.753, 261.913, 247.435,
  243.28, 307.205, 228.997,
  352.863, 366.408, 268.928,
  413.422, 393.576, 410.009,
  618.972
)

#let positions = range(4, 41, step: 3)

#let re(t, i) = calc.round(calc.abs(float(t.children.at(i * 3 + 4).text) - float(calibration_exact_values.at(i))) / float(calibration_exact_values.at(i)) * 100, digits: 2)

#let ts1 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [70],
  [tsp25_2.dat], [261.913], [92],
  [tsp25_3.dat], [251.863], [89],
  [tsp50_1.dat], [243.28], [526],
  [tsp50_2.dat], [310.844], [518],
  [tsp50_3.dat], [234.029], [602],
  [tsp75_1.dat], [357.348], [1503],
  [tsp75_2.dat], [373.241], [1501],
  [tsp75_3.dat], [271.106], [1545],
  [tsp100_1.dat], [433.38], [3405],
  [tsp100_2.dat], [396.052], [3054],
  [tsp100_3.dat], [417.588], [3444],
  [tsp200_1.dat], [657.699], [26939],
)

#let ts2 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [66],
  [tsp25_2.dat], [261.913], [77],
  [tsp25_3.dat], [251.863], [77],
  [tsp50_1.dat], [244.243], [464],
  [tsp50_2.dat], [312.615], [437],
  [tsp50_3.dat], [234.029], [475],
  [tsp75_1.dat], [357.348], [1423],
  [tsp75_2.dat], [374.678], [1344],
  [tsp75_3.dat], [271.106], [1388],
  [tsp100_1.dat], [433.38], [3097],
  [tsp100_2.dat], [409.831], [3078],
  [tsp100_3.dat], [417.588], [3293],
  [tsp200_1.dat], [657.699], [24590],
)

#let ts3 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [75],
  [tsp25_2.dat], [261.913], [99],
  [tsp25_3.dat], [251.863], [100],
  [tsp50_1.dat], [243.28], [511],
  [tsp50_2.dat], [310.844], [540],
  [tsp50_3.dat], [233.074], [569],
  [tsp75_1.dat], [356.898], [1509],
  [tsp75_2.dat], [373.241], [1546],
  [tsp75_3.dat], [271.106], [1966],
  [tsp100_1.dat], [432.134], [3507],
  [tsp100_2.dat], [396.681], [3304],
  [tsp100_3.dat], [417.588], [3657],
  [tsp200_1.dat], [657.699], [27243]
)

#let ts4 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [81],
  [tsp25_2.dat], [261.913], [104],
  [tsp25_3.dat], [251.863], [133],
  [tsp50_1.dat], [243.28], [553],
  [tsp50_2.dat], [308.323], [616],
  [tsp50_3.dat], [231.974], [545],
  [tsp75_1.dat], [356.782], [1533],
  [tsp75_2.dat], [373.241], [1584],
  [tsp75_3.dat], [271.106], [1818],
  [tsp100_1.dat], [429.465], [3631],
  [tsp100_2.dat], [396.681], [3448],
  [tsp100_3.dat], [414.882], [3574],
  [tsp200_1.dat], [648.692], [25816]
)

#let ts5 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [98],
  [tsp25_2.dat], [261.913], [110],
  [tsp25_3.dat], [251.863], [124],
  [tsp50_1.dat], [243.28], [608],
  [tsp50_2.dat], [308.323], [632],
  [tsp50_3.dat], [231.365], [565],
  [tsp75_1.dat], [356.782], [1493],
  [tsp75_2.dat], [373.241], [1630],
  [tsp75_3.dat], [271.106], [1899],
  [tsp100_1.dat], [427.899], [3598],
  [tsp100_2.dat], [396.681], [3480],
  [tsp100_3.dat], [414.882], [3508],
  [tsp200_1.dat], [647.64], [25770]
)

#let ts6 = table(
  columns: (auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*Solution*], [*Execution time (ms)*],
  [tsp25_1.dat], [179.753], [10],
  [tsp25_2.dat], [261.913], [12],
  [tsp25_3.dat], [251.863], [16],
  [tsp50_1.dat], [243.28], [141],
  [tsp50_2.dat], [308.323], [261],
  [tsp50_3.dat], [231.974], [213],
  [tsp75_1.dat], [356.782], [864],
  [tsp75_2.dat], [373.241], [600],
  [tsp75_3.dat], [271.106], [781],
  [tsp100_1.dat], [427.899], [4192],
  [tsp100_2.dat], [396.681], [1949],
  [tsp100_3.dat], [414.882], [2251],
  [tsp200_1.dat], [647.64], [43012]
)

#let errors = table(
  
  columns: (auto, auto, auto, auto, auto, auto, auto),
  inset: 10pt,
  align: center,
  [], [*TS1*], [*TS2*], [*TS3*], [*TS4*], [*TS5*], [*TS6*],
  [tsp25_1.dat], [#re(ts1, 0)], [#re(ts2, 0)], [#re(ts3, 0)], [#re(ts4, 0)], [#re(ts5, 0)], [#re(ts6, 0)],
  [tsp25_2.dat], [#re(ts1, 1)], [#re(ts2, 1)], [#re(ts3, 1)], [#re(ts4, 1)], [#re(ts5, 1)], [#re(ts6, 1)],
  [tsp25_3.dat], [#re(ts1, 2)], [#re(ts2, 2)], [#re(ts3, 2)], [#re(ts4, 2)], [#re(ts5, 2)], [#re(ts6, 2)],
  [tsp50_1.dat], [#re(ts1, 3)], [#re(ts2, 3)], [#re(ts3, 3)], [#re(ts4, 3)], [#re(ts5, 3)], [#re(ts6, 3)],
  [tsp50_2.dat], [#re(ts1, 4)], [#re(ts2, 4)], [#re(ts3, 4)], [#re(ts4, 4)], [#re(ts5, 4)], [#re(ts6, 4)],
  [tsp50_3.dat], [#re(ts1, 5)], [#re(ts2, 5)], [#re(ts3, 5)], [#re(ts4, 5)], [#re(ts5, 5)], [#re(ts6, 5)],
  [tsp75_1.dat], [#re(ts1, 6)], [#re(ts2, 6)], [#re(ts3, 6)], [#re(ts4, 6)], [#re(ts5, 6)], [#re(ts6, 6)],
  [tsp75_2.dat], [#re(ts1, 7)], [#re(ts2, 7)], [#re(ts3, 7)], [#re(ts4, 7)], [#re(ts5, 7)], [#re(ts6, 7)],
  [tsp75_3.dat], [#re(ts1, 8)], [#re(ts2, 8)], [#re(ts3, 8)], [#re(ts4, 8)], [#re(ts5, 8)], [#re(ts6, 8)],
  [tsp100_1.dat], [#re(ts1, 9)], [#re(ts2, 9)], [#re(ts3, 9)], [#re(ts4, 9)], [#re(ts5, 9)], [#re(ts6, 9)],
  [tsp100_2.dat], [#re(ts1, 10)], [#re(ts2, 10)], [#re(ts3, 10)], [#re(ts4, 10)], [#re(ts5, 10)], [#re(ts6, 10)],
  [tsp100_3.dat], [#re(ts1, 11)], [#re(ts2, 11)], [#re(ts3, 11)], [#re(ts4, 11)], [#re(ts5, 11)], [#re(ts6, 11)],
  [tsp200_1.dat], [#re(ts1, 12)], [#re(ts2, 12)], [#re(ts3, 12)], [#re(ts4, 12)], [#re(ts5, 12)], [#re(ts6, 12)],
)