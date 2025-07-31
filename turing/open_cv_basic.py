#! /usr/bin/python3
import numpy as np

# Given a kernel, develop a function that applies the kernel to an image. It should be used without padding and with a stride of 1. If input image size is N  M, the output image size should be (N - 2)  (M - 2) with a kernel size 3 * 3


class Solution:
    def solution(self, image, kernel):
        n, m = image.shape

        output_img = np.zeroes(n - 2, m - 2)

        for i in range(1, n - 1):
            for j in range(1, m - 1):
                extract_img = image[i - 1: i + 2, j - 1: j + 2]

                rslt = np.sum(extracted_img * kernel)
                output_img[i - 1, j - 1] = rslt

            return output_img


def main():
    image = np.array(
        [
            [1, 2, 3, 4, 5],
            [6, 7, 8, 9, 10],
            [11, 12, 13, 14, 15],
            [16, 17, 18, 19, 20],
            [21, 22, 23, 214, 25],
        ]
    )
    kernel = np.array([1, 0, -1], [1, 0, -1], [1, 0, -1])

    ans = Solution().solution(image, kernel)

    print(ans)


if __name__ == "__main__":
    main()
