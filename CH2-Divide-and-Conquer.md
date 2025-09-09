# CH2 Divide and Conquer

# 1. Maxima in the Plane

## 1.1 Problem Description

Consider a set of $n$ 2-D points:

```math
P=\{p_{1}, p_{2}, \cdots, p_{n}\}
```

where each point is represented by its $x$ and $y$ coordinate:

```math
p_{i} = (x_{i}, y_{i}), \ i \in [0, n]
```

**`local def`** We define that $p_{i}$ **dominates** $p_{j}$ if:

```math
x_{i} > y_{i} \land x_{j} > y_{j}
```

**`local def` Maxima**

The **Maxima** is a subset of $P$ where every point in the Maxima is not dominated by other points.

![](asset/ch-2/maxima-example.png)

**`goal`** Given such set of 2-D points $P$, we want to find its Maxima.

## 1.2 Problem Solution

We divide the $n$ points into arbitrarily two halves. Suppose that we obtained both halves' Maxima. We now merge the two solutions.

<img src="asset/ch-2/maxima-dc-0.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

<html>
    <table>
        <tr>
            <th>Graph</th>
            <th>Description</th>
        </tr>
        <tr>
            <td>
                <img src="asset/ch-2/maxima-dc-1.png"/>
            </td>
            <td style="max-width:200px">
                First, p and q relatively points to the leftmost maxima of blue and red. We can safely declare that the blue one is the overall maxima.
            </td>
        </tr>
        <tr>
            <td>
            <img src="asset/ch-2/maxima-dc-2.png"/>
            </td>
            <td style="max-width:200px">
                Pointer p proceeds, finding that the first and second points in the red set are bounded by p. Therefore, this p is the overall Maxima.
            </td>
        </tr>
        <tr>
            <td>
            <img src="asset/ch-2/maxima-dc-3.png"/>
            </td>
            <td style="max-width:200px">
                Now, p is bounded by q. Therefore, q is the overall maxima.
            </td>
        </tr>
        <tr>
            <td>
            <img src="asset/ch-2/maxima-dc-4.png"/>
            </td>
            <td style="max-width:200px">
                No more p. Then q is the overall maxima.
            </td>
        </tr>
    </table>
</html>

## 1.3 Complexity

Merging takes $O(n)$ time. Therefore, we have the following recurrence:

```math
T(n) \leq \underbrace{2 \cdot T(\frac{n}{2})}_{\text{Each part}} + \underbrace{O(n)}_{\text{Merge}}
```

Namely, $T(n) = O(n \log n)$

# 2. Closest Pair in the Plane

## 2.1 Problem Description

Consider the point set $P$ given in the first problem.

**`local def`** We define that, $p_{i}$ and $p_{j}$ is the **closest pair** if the distance between them is the minimum among all distinct pairs of input points. Namely:

```math
\neg \exists a, b, \  \text{dist}(p_{i}, p_{j}) > \text{dist}(p_{a}, p_{b})
```

**`goal`** Given such set of 2-D points $P$, find the closest pair $(p_{i}, p_{j})$.

## 2.2 Problem Solution

Suppose we have found the closest pair $(p_{i}, p_{j})$ in the leftmost and rightmost $\frac{n}{2}$ points, respectively. 

```math
\delta_{1}, \delta_{2}
```

We now merge the two solutions.

<img src="asset/ch-2/closest-pair-0.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

We now need to identify, whether there exists a pair of points with a smaller distance than $\delta_{1}$ and $\delta_{2}$, where each point belongs to different sub-sets.

<img src="asset/ch-2/closest-pair-dc-1.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

### 2.2.1 Limit $x$ Coordinate

We identify the smaller distance among the two obtained solutions.

```math
\delta = \min(\delta_{1}, \delta_{2})
```

We put a two-way limit with width $2\delta$ evenly around the division point of the left and right sub-sets. Now, only points within the middle region is worthy of inspecting.

<img src="asset/ch-2/closest-pair-dc-2.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

If any of the point of the inspected cross-set pair is out of this region, the $x$ distance will already be larger than $\delta$, making it useless.

### 2.2.2 Limit $y$ Coordinate

`sub-figure (a)` For an arbitrary point within the delta-region, we put a two-way limit with height $2\delta$ around the $x$ axis of that point evenly.

<img src="asset/ch-2/closest-pair-dc-3.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

For this point specifically. Any point out of this region is useless, since its $y$ distance will already be larger than $\delta$. The pairing point should always lie in the gray area.

**`fact`** `sub-figure (c)` The gray area can have atmost 6 points. There are $O(1)$ points inside the gray rectangle.

**`informal-proof`** `sub-figure (b)` If we have a point in an arbitrary region in the gray area, there will be no points within a dashed-circle of radius $\delta$ from it. Otherwise, the distance between the second point to the circle's center will be smaller than $\delta$, leading to a contradiction.

### 2.2.3 Two Scans

<img src="asset/ch-2/closest-pair-dc-4.png" style="display: block; width: 250px; margin: 0 auto;"/>

<br>

There are two top-to-bottom scans from the left to the right.

Take the first scan as an example, where left points are iterated to scan the right points. At each left point, scan the right list from the current position until the next point falls out the gray square. This takes $O(1)$ time.

> Notice that, since we will use right points to scan the left bottom as well, we don't scan the top square during the left-scan.

Both scans have at most $O(\frac{n}{2})$, so the scanning time is $O(n)$.

## 2.3 Complexity

At each stage, we:

- Make two recursive calls to obtain the left and right minimum distances.
- Spend $O(n\log n)$ to sort all the points.
- Spend $O(n)$ time to scan the boundary.

In summary, each recursive call takes $O(n\log n)$ time.

Consequently, the overall recurrence is:

```math
T(n) \leq 2T(\frac{n}{2}) + O(n\log n)
```

Leading to $T(n) = O(n (\log n)^{2})$.

## 2.4 Enhance Sorting

We don't need to sort the points at every recursive call. We can sort them once in for all.

Sort the points into unified two doubly-linked lists with respect to the $x$ and $y$ coordinates.

<img src="asset/ch-2/closest-pair-dc-5.png" style="display: block; width: 400px; margin: 0 auto;"/>

<br>

*(The respective link view.)*

<br>

<img src="asset/ch-2/closest-pair-dc-6.png" style="display: block; width: 400px; margin: 0 auto;"/>

<br>

*(The true, unified link view, in x-perspective.)*

## 2.5 Complexity After Enhancement

Initially:

- We sort the points twice in $O(n \log n)$ time.

At each recursive call, we:

- Scan through the $x$ - List from the middle to filter out middle points, in $O(n)$ time.
- For left and right subset within the middle area, we use cross-reference pointers to get their $y$ orders, in $O(n)$ time. 
- We then scan the middle area twice, in $O(n)$ time.

In summary, each recursive call takes $O(n)$ time.

<img src="asset/ch-2/closest-pair-dc-7.png" style="display: block; width: 400px; margin: 0 auto;"/>

<br>

Consequently, ignoring the cost of sorting, the overall recurrence is:

```math
T(n) \leq 2 \cdot T(\frac{n}{2}) + O(n)
```

Resulting in $T(n) = O(n \log n)$. This still remains after the initial sorting cost is added since:

```math
\begin{align}
T(n) + O(n \log n) &= 2 \cdot O(n \log n) \\
&= O(n \log n)
\end{align}
```

# 3. k-th Smallest Number
