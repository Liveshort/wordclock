import numpy as np

mode = "CRGB"
gold = np.array([255, 215, 0], dtype="int")
orange = np.array([255, 165, 0], dtype="int")
red = np.array([255, 69, 0], dtype="int")

limegreen = np.array([50, 205, 50], dtype="int")
yellowgreen = np.array([154, 205, 50], dtype="int")
yellow = np.array([225, 225, 10], dtype="int")

deepskyblue = np.array([0, 191, 255], dtype="int")
aqua = np.array([0, 235, 235], dtype="int")
royalblue = np.array([65, 105, 225], dtype="int")

aliceblue = np.array([240, 248, 255], dtype="int")
ghostwhite = np.array([248, 248, 255], dtype="int")
snow = np.array([255, 250, 250], dtype="int")


schemes = [ (gold, orange, red, orange, gold),
            (limegreen, yellowgreen, yellow, yellowgreen, limegreen),
            (deepskyblue, aqua, royalblue, aqua, deepskyblue),
            (aliceblue, ghostwhite, snow, ghostwhite, aliceblue) ]

scheme_names = ["fireColorScheme", "forestColorScheme", "skyColorScheme", "whiteColorScheme"]

for s, sn in zip(schemes, scheme_names):
    print("const CRGB {}[48] = {{ ".format(sn), end="")
    for i in range(4):
        src = s[i]
        trg = s[i+1]

        for j in range(12):
            cur = np.array((6 - j)/6 * src + j/6 * trg, dtype="int")

            if i == 0 and j == 0:
                print("{}({},{},{})".format(mode, cur[0], cur[1], cur[2]), end="")
            else:
                print(", {}({},{},{})".format(mode, cur[0], cur[1], cur[2]), end="")
    print(" };")
