Алгоритм Холла реализует итерационный процесс выборов и перевыборов представителей
подмножеств заданного семейства в порядке роста их индексов, а номер каждого представителя
в искомой системе различных представителей идентифицирует подмножество, откуда он выбран.
На каждой итерации i от 1 до  m представителем очередного подмножества S_i выбирается его минимальный (по номеру)
свободный элемент E_j, который не входит в текущую частичную трансверсаль T_(i-1) из представителей ранее рассмотренных подмножеств.

