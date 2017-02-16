import numpy as np
import matplotlib.pyplot as plt

n = np.array([10,11,12,13,14,15])
n[0] = 2111.399902,1064.900024,503.799988,251.800003,128.399994,70.400002,34.799999,16.500000,10.900000
n[1] = 4207.299805,2159.000000,1059.900024,531.400024,261.299988,132.800003,71.099998,33.799999,18.000000,15.200000
n[2] = 8597.700195,4176.200195,2191.100098,1079.400024,514.299988,265.799988,130.100006,71.099998,29.400000,16.900000,9.400000
n[3] = 17286.199219,8354.599609,6586.500000,2116.500000,1080.599976,559.900024,1572.099976,135.000000,70.800003,31.000000,15.400000,9.100000
n[4] = 33685.101562,16153.400391,7958.100098,3921.500000,1983.199951,980.400024,500.500000,260.399994,130.500000,69.900002,32.599998,17.100000,9.000000
n[5] = 64823.800781,32179.699219,15964.599609,7842.700195,4224.200195,1999.500000,993.000000,507.899994,251.500000,130.300003,70.800003,34.700001,15.900000,9.100000
n[6] = 129384.601562,64901.699219,36421.500000,15713.400391,7908.399902,4005.100098,2027.800049,1049.300049,519.299988,256.200012,134.300003,69.199997,32.500000,16.900000,8.500000
n[7] = 264196.093750,131166.406250,68972.796875,31478.400391,15857.200195,8268.099609,4816.500000,2624.399902,1400.199951,563.299988,288.500000,143.399994,72.599998,35.900002,18.600000,9.200000
n[8] = 672138.312500,273570.187500,133673.296875,62919.300781,31683.199219,16613.400391,15729.099609,5735.799805,4003.199951,1120.000000,566.400024,284.399994,140.199997,72.599998,34.099998,16.200001,9.00000
n[9] = 1261074.125000,559586.625000,305409.000000,129285.703125,65063.699219,33696.101562,17335.500000,9330.400391,8670.700195,4976.799805,1106.699951,556.099976,274.700012,142.600006,77.199997,39.200001,16.600000,10.900000
n[10] = 2395923.250000,1073147.250000,514908.500000,260260.593750,131275.203125,65338.000000,35593.699219,17475.800781,8179.299805,4104.299805,2095.000000,1058.300049,524.099976,263.700012,139.000000,75.400002,38.599998,16.400000,10.600000
n[11] = 4473891.000000,2189784.000000,1057751.250000,545386.875000,324075.906250,195617.296875,121010.101562,58273.199219,33947.199219,17584.500000,8056.000000,3978.899902,1864.500000,615.099976,276.399994,138.600006,75.400002,36.700001,17.200001,10.600000
n[12] = 8785550.000000,4297557.000000,2178351.250000,1210121.750000,790102.687500,699126.125000,360161.406250,182001.593750,112856.703125,56013.800781,27303.199219,14205.200195,9372.900391,3694.899902,2340.899902,346.100006,136.500000,74.099998,38.900002,16.500000,10.800000
n[13] = 17575224.000000,8608942.000000,4452766.500000,2441661.500000,1683589.250000,1601663.750000,766421.000000,407085.187500,258564.796875,120076.796875,59362.101562,31536.000000,16065.099609,7861.899902,4242.399902,2043.099976,559.200012,137.300003,72.900002,36.400002,16.700001,10.800000
n[14] = 34993000.000000,17580476.000000,8832759.000000,4955171.000000,3383132.500000,3150250.500000,1564915.250000,833305.375000,509559.906250,253460.406250,120671.398438,61164.500000,32639.599609,17626.599609,8362.099609,3993.800049,1985.699951,747.599976,143.500000,74.000000,39.900002,18.400000,12.100000
n[15] = 69436568.000000,34862272.000000,17574704.000000,9801970.000000,7065517.000000,7095681.500000,3376904.750000,1709534.750000,1034989.812500,562147.687500,239784.093750,142068.203125,70379.398438,33491.101562,18046.199219,11010.200195,3926.699951,2276.800049,1194.099976,171.300003,74.099998,38.299999,16.799999,10.800000

n_val = np.array([2**10, 2**11, 2**12, 2**13, 2**14, 2**15, 2**16, 2**17, 2**18, 2**19, 2**20, 2**21, 2**22, 2**23, 2**24, 2**25])


t = np.arange(0.0, 2.0, 0.01)
s1 = np.sin(2*np.pi*t)
s2 = np.sin(4*np.pi*t)

plt.figure(1)
plt.subplot(211)
plt.plot(t, s1)
plt.subplot(212)
plt.plot(t, 2*s1)

plt.figure(2)
plt.plot(t, s2)

# now switch back to figure 1 and make some changes
plt.figure(1)
plt.subplot(211)
plt.plot(t, s2, 's')
ax = plt.gca()
ax.set_xticklabels([])

plt.show()